Import("env")

import os
import configparser

settings_file = "settings.conf"

if os.path.isfile(settings_file):
    config = configparser.ConfigParser()
    config.read(settings_file)
    defines = []
    for key in config["ENV"]:
        defines.append([key.upper(), config["ENV"][key]])
    env.Append(CPPDEFINES=defines)   
