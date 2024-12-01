db = db.getSiblingDB('TESA');

// Create collections
db.createCollection('report');
db.createCollection('model');
db.createCollection('sound');

// Optional: Insert sample data
db.report.insertOne({ exampleField: 'Sample Report Data' });
db.model.insertOne({ exampleField: 'Sample Model Data' });
db.sound.insertOne({ deviceId: "testinlocal", timeStamp: new Date(), filePath: "/static/sound/test.wav" });

print('Initialized MongoDB with collections: report, model, sound');
