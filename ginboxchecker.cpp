#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include </usr/local/include/curl/curl.h>
size_t writer( char *ptr, size_t size, size_t nmemb, void *userdata) {
   size_t realsize=size*nmemb;
   std::string *out = reinterpret_cast<std::string *>(userdata);
   out->append(ptr, realsize);
   return realsize;
}

CURLcode connectImap(std::string *buffer) {
  CURL *curl;
  CURLcode res = CURLE_OK;
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
    curl_easy_setopt(curl, CURLOPT_USERNAME,"myemail@gmail.com");
    curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER,"theaccesstoken");
    curl_easy_setopt(curl, CURLOPT_URL, "imaps://imap.gmail.com:993/INBOX");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SEARCH UNSEEN");
    res = curl_easy_perform(curl);
  }
  curl_easy_cleanup(curl);
  return res;
}

void notifyByVoice(ctr) {
  std::stringstream cmd;
  cmd<<"say \"You have "<<ctr<<" new message"<<(ctr>1?"s":"")<<"!\"";
  system(cmd.str().c_str());
}
 
int main(void)
{
  std::string str;
  CURLcode res = connectImap(&str);
  while(!res) {
    int tmp;
    int ctr=0;
    std::stringstream lineStream(str);
    lineStream>>str;
    lineStream>>str;
    while(lineStream >> tmp) {
      ++ctr;
    }
    notifyByVoice(ctr);
    sleep(300);
    res = connectImap(&str);
  }
  if(res) {
    printf("Something went wrong.\n");
  }
  return (int)res;
}
