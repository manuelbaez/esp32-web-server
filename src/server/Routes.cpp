#include "Files.h" 
#include "Routes.h" 

void addRoutes(ESP8266WebServer* server){ 
	server->on("/bg.4353c7bb.svg",[server]() {server->send(200, "image/svg", bg_4353c7bb_svg, sizeof(bg_4353c7bb_svg));} ); 
	server->on("/index.html",[server]() {server->send(200, "text/html", index_html, sizeof(index_html));} ); 
	server->on("/main.cc6f8036.js",[server]() {server->send(200, "text/javascript", main_cc6f8036_js, sizeof(main_cc6f8036_js));} ); 
	server->on("/page-layout.c28e8034.css",[server]() {server->send(200, "text/css", page_layout_c28e8034_css, sizeof(page_layout_c28e8034_css));} ); 
}