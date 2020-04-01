import os
import mime

ingest_directory = "{base_path}/dist/output".format(base_path=os.getcwd())

routes_file= '#include "Files.h" \n#include "Routes.h" \n\nvoid addWebAppRoutes(ESP8266WebServer* server){ \n'
array_file="#include<stdint.h> \n\n"
for filename in os.listdir(ingest_directory):
   if(".map" in filename):
      continue
   with open(os.path.join(ingest_directory, filename), 'rb') as file:
      data = file.read()
      variable_name=filename.replace(".","_").replace("-","_")
      mime_type=mime.Types.of(os.path.join(ingest_directory, filename))[0]
      routes_file+='\tserver->on("/{filename}",[server]() {{server->send(200, "{content_type}", {variable_name}, sizeof({variable_name}));}} ); \n'.format(filename=filename, variable_name=variable_name, content_type=mime_type)
      array_file+="const uint8_t {variable}[]={{".format(variable=variable_name)
      for byte in data:
         array_file+="{},".format(byte)
      array_file+="}; \n"
routes_file+="}"

with open("../include/Files.h", 'w') as cpp_files_bundle:
   cpp_files_bundle.write(array_file)
   cpp_files_bundle.close()

with open("../src/server/WebAppRouter.cpp", 'w') as cpp_routes:
   cpp_routes.write(routes_file)
   cpp_routes.close()

# with open("./cpp-bundle/Routes.h", 'w') as cpp_routes_header:
#    cpp_routes_header.write('#include "ESP8266WebServer.h" \n\nvoid addWebAppRoutes(ESP8266WebServer* server);')
#    cpp_routes_header.close()