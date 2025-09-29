# mmWave Example/Demo Order:
This list provides the most logical order for exploring the demos
and gives an idea of what the demos will demonstrate and which functionalities will
be used in the actual Spot and Shot project. The order is based on the difficulty and
the progressive functionality that each demo uses relative to the previous demo.
(The explanation of the demos is based on ChatGPT, so this needs to be double-checked.)

1. **Object Detection:**
   - Normal object detection

2. **odsdemo:**
   - Should also have scene classification (e.g., determining if objects are stationary or moving).

3. **High Accuracy:**
   - Tracks objects with high precision
   - Kalman Filter-based MHT (Multiple Hypothesis Tracking)
   - Uses CFAR + clustering + tracking
   - Provides object position, velocity, and ID
   - General tracking (indoor/outdoor): Vehicle tracking, general object tracking

4. **3D People Counting or High Accuracy People Tracking:**
   - Tracks and counts multiple people in real time
   - GNN-based Kalman Filter (Global Nearest Neighbor)
   - Uses CFAR + DBSCAN + tracking
   - Provides 3D people positions with trajectory tracking
   - Optimized for indoor human movement: People counting, occupancy monitoring

