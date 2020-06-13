/*
 * meteodata-git
 * Stanislaw Grams <sjg@fmdx.pl>
 *
 * src/agent.cc
 * See ../LICENSE for license information
 */
#include "../include/agent.hh"

std::atomic<agent_c *> agent_c::agent_instance{nullptr};
std::mutex             agent_c::agent_mutex;

agent_c::agent_c ()
{
  curl_global_init (CURL_GLOBAL_DEFAULT);
}

agent_c::~agent_c () {
  curl_global_cleanup ();
}

void
agent_c::delete_instance () {
  agent_c *ptr = agent_instance.load (std::memory_order_acquire);
  if (nullptr != ptr) {
    ptr = agent_instance.load (std::memory_order_relaxed);
    if (nullptr != ptr) {
      delete ptr;
      agent_instance.store (nullptr, std::memory_order_release);
      agent_mutex.unlock ();
    }
  }
}

agent_c *
agent_c::fetch_instance () {
  agent_c *ptr = agent_instance.load (std::memory_order_acquire);
  if (nullptr == ptr) {
    std::lock_guard<std::mutex> lock (agent_mutex);
    ptr = agent_instance.load (std::memory_order_relaxed);
    if (nullptr == ptr) {
      ptr = new agent_c ();
      agent_instance.store (ptr, std::memory_order_release);
    }
  }
  return ptr;
}

size_t
agent_c::curl_callback (
  char *in,
  size_t size,
  size_t nmemb,
  std::string *out
  )
{
  size_t realsize = size * nmemb;
  if (in == NULL || out == NULL) {
    throw std::invalid_argument ("parameters set incorrectly");
    return 0;
  }
  out->append (in, realsize);
  return realsize;
}

int
agent_c::curl_retrieve (
  std::string url,
  std::string *buffer
  )
{
  CURLcode status;
  CURL     *conn = curl_easy_init ();
  if (conn == NULL) {
    return -1;
  }
  curl_easy_setopt (conn, CURLOPT_URL, url.c_str ());
  curl_easy_setopt (conn, CURLOPT_TIMEOUT, AGENT_TIMEOUT);
  curl_easy_setopt (conn, CURLOPT_WRITEFUNCTION, curl_callback);
  curl_easy_setopt (conn, CURLOPT_WRITEDATA, buffer);
  curl_easy_setopt (conn, CURLOPT_USERAGENT, AGENT_USERAGENT);

  status = curl_easy_perform (conn); // fetch data
  curl_easy_cleanup (conn); // cleanup

  return (status == CURLE_OK) ? 0 : status;
}

int
agent_c::idfetcher_execute (
  std::string name,
  data_c *data
  )
{
  int status = 0;
  std::string url;

  if (data == NULL || name.length () <= 0) {
    return -1;
  }

  // build an url
  url = std::string (AGENT_IDFETCHER_URI_PREFIX + name +
    AGENT_IDFETCHER_URI_SUFFIX);

  status = this->curl_retrieve (url, &data->buffer);
  return status;
}

int
agent_c::datafetcher_execute (
  uint64_t id,
  data_c   *data,
  flavour_t flavour
  )
{
  long        status = 0;
  std::string url;

  if (data == NULL || id == 0) {
    return -1;
  }

  // build an url
  if (flavour == meteo) {
    url = std::string (AGENT_DATAFETCHER_METEO_URI);
  } else if (flavour == hydro) {
    url = std::string (AGENT_DATAFETCHER_HYDRO_URI);
  }
  url += std::to_string (id);

  status = this->curl_retrieve (url, &data->buffer);
  return status;
}
