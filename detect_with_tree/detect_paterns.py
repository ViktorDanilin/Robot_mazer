import cv2
import dlib
import os
import xml.etree.ElementTree as pars
#######################################
dir=r"C:\Users\1\Desktop\project_cv\words"
images=[]
annots=[]

imgNameList = os.listdir(dir + "/images")

print(imgNameList)

for FileName in imgNameList:
    image = cv2.imread(dir + "/images/" + FileName)
    image=cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    
    OnlyFileName = FileName.split(".")[0]  
    print(OnlyFileName)
    e = pars.parse(dir + "/annotations/" + OnlyFileName + ".xml")
    root = e.getroot()
    object = root.find("object")
    object = object.find("bndbox")
    x = int(object.find("xmin").text)
    y = int(object.find("ymin").text)
    x2 = int(object.find("xmax").text)
    y2 = int(object.find("ymax").text)
    
    images.append(image)
    annots.append([dlib.rectangle(left=x, top=y, right=x2,bottom=y2)])
    
options = dlib.simple_object_detector_training_options()
options.be_verbose=True

detector = dlib.train_simple_object_detector(images,annots,options)

detector.save("tld.swm")    
print("Detector saved")
model_detector = dlib.simple_object_detector("tld.swm")
#######################################################
cap=cv2.VideoCapture(0)


while(True):
  ret,frame=cap.read()
  
  boxes = model_detector(frame)
  for box in boxes:
    print("True")
    (x,y,xb,yb) = [box.left(),box.top(),box.right(),box.bottom()]
    cv2.rectangle(frame, (x,y),(xb,yb),(0,0,225),2)
 
  cv2.imshow("frame",frame)

  if cv2.waitKey(1)==ord("q"):
      break
    
cap.release()
cv2.destroyAllWindows()