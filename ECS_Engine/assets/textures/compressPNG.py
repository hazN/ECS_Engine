# import required module
import os
import sys

# assign directory
try:
    directory=os.path.dirname(os.path.realpath(sys.argv[1]))
    print(directory)
except:
    print('Please pass directory')
# iterate over files in
# that directory
for filename in os.listdir(directory):
    if(filename.lower().endswith(('.png'))):
        filenoext = filename.rsplit( ".", 1 )[ 0 ];
        if not (os.path.exists(directory + "/" + filenoext + ".pvr")):
            tempName = "tempFile.png";
            pngquant = "pngquant --speed 2 --quality=65-80 " + filename + " --output " + tempName
            os.system('cmd /c ' + pngquant)
            optipng = "optipng -k " + tempName + " -force"
            os.system('cmd /c ' + optipng)
            pvrtextool = "PVRTexToolCLI.exe -i " + tempName + " -o " + filenoext + ".pvr -f ETC1,UBN,lRGB -q pvrtcfast"
            os.system('cmd /c ' + pvrtextool)
            os.remove(tempName)
            os.remove(tempName + ".bak")
print("Build Script Complete!")
