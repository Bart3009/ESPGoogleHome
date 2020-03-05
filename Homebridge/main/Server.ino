void server_request() {
  if (header.indexOf("GET /light_bedroom") >= 0) {
    light_Bedroom();
  }
}


void server_publish() {
  if (header.indexOf("GET /state/light_bedroom") >= 0) {
  }
}
