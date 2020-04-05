import cv2 as cv

cap=cv.VideoCapture(0)
while(True):
  ret,frame=cap.read()
  cv.imshow("frame",frame)
#  print(frame)
  if cv.waitKey(1)==ord("q"):
      break
cap.release()
cv.destroyAllWindows()