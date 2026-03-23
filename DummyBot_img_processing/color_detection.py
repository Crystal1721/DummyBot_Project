from ultralytics import YOLO

model = YOLO("best.pt")
results = model.predict(source="2", show=True, conf=0.60)

