# WycieczkaRobotow
GUI based simulation engine for displaying movements of robot formation traveling along desired path

TO RUN EXAMPLE SIMULATION:
1. Open WycieczkaRobotow.pro with QtCreator and build it
2. Open ./FollowTheLeader_SimulationExample/FollowTheLeader_SimulationExample.pro and build it
3. Assure that the resultant file from step 2 (Simulation.exe) is in the same directory as the resultant
   file from step 1 (WycieczkaRobotow.exe). Copy the files to the common directory if needed.
4. Copy the ./result/data directory to the directory containing the executable files mentioned above
5. - Run WycieczkaRobotow from the QtCreator, OR 
   - Place all the necessary .dll files in the directory together with executable files (.dll files may
     be found in ./result)
OR

Try to run already built WycieczkaRobotow.exe from ./result


HOW TO USE:
- in the top right corner draw a desired path that the robot formation will run, click Accept button
  + a path must be a single curve that can be drawn by left mouse button click and holding it while drawing
  + a path must contain at least two points
  + click Clear button if you want to redraw a path
  + if don't want to draw a path, you can provide your custom file with point coordinates. Path to the file and its format must be the         same as would be originally generated from the program
- in the bottom right corner push some buttons to define a robot formation, click Accept button
  + the pushed buttons symbolize a robot formation
  + click Clear button if you want to redefine a formation or just push/unpush another buttons
  + FollowTheLeader_SimulationExample assumes that the pushed buttons define a formation at the moment all the robots look to the right
  + if don't want to define a formation, you can provide your custom file with point coordinates. Path to the file and its format must be     the same as would be originally generated from the program  
- click Start simulation to start the simulation
