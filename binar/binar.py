import cv2
def nothing(x):
    pass

cap=cv2.VideoCapture(0)

cv2.namedWindow("result")
cv2.createTrackbar("minb","result",0,255,nothing)
cv2.createTrackbar("ming","result",0,255,nothing)
cv2.createTrackbar("minr","result",0,255,nothing)

cv2.createTrackbar("maxb","result",0,255,nothing)
cv2.createTrackbar("maxg","result",0,255,nothing)
cv2.createTrackbar("maxr","result",0,255,nothing)


while(True):

  ret,frame=cap.read()
  hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
  cv2.imshow("hsv",hsv)
  minb = cv2.getTrackbarPos("minb","result")
  ming = cv2.getTrackbarPos("ming", "result")
  minr = cv2.getTrackbarPos("minr", "result")

  maxb = cv2.getTrackbarPos("maxb", "result")
  maxg = cv2.getTrackbarPos("maxg", "result")
  maxr = cv2.getTrackbarPos("maxr", "result")



  mask = cv2.inRange(hsv,(minb,ming,minr),(maxb,maxg,maxr))
  cv2.imshow("mask",mask)
  result = cv2.bitwise_and(frame,frame, mask = mask)
  cv2.imshow("result",result)
  if cv2.waitKey(1)==ord("q"):
      break
cap.release()
cv2.destroyAllWindows()




