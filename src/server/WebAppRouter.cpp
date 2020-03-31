#include "Files.h" 
#include "Routes.h" 

void addWebAppRoutes(ESP8266WebServer* server){ 
	server->on("/bg.4353c7bb.svg",[server]() {server->send(200, "image/svg+xml", bg_4353c7bb_svg, sizeof(bg_4353c7bb_svg));} ); 
	server->on("/index.html",[server]() {server->send(200, "text/html", index_html, sizeof(index_html));} ); 
	server->on("/input.c53c4996.css",[server]() {server->send(200, "text/css", input_c53c4996_css, sizeof(input_c53c4996_css));} ); 
	server->on("/main.ec09f739.js",[server]() {server->send(200, "text/javascript", main_ec09f739_js, sizeof(main_ec09f739_js));} ); 
	server->on("/page-layout.885bf40b.css",[server]() {server->send(200, "text/css", page_layout_885bf40b_css, sizeof(page_layout_885bf40b_css));} ); 
} 
