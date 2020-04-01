import os
import shutil

shutil.rmtree("./web/dist")
os.system("cd ./web && npm run build")