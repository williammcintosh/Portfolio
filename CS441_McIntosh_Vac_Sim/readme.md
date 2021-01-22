# Vacuum Cleaner Simulator

To run the simulator, click this link:
http://bridgeworxgames.com/CS441_Vac_Sim/

This is a WebGL rendering of a Unity project where I coded agent simulation policies/logic in C# for a vacuum cleaning robot to navigate a grid world. The project helps to study optimal policies/cost functions.

The main purpose of this exercise is to recognize how inefficient relex agents are. It is very difficult to code every single situation or scenario that the agent is able to come into contact with (which would be called a Rule Table). The primary shortcoming of a reflex agent is its inability to store memory, so it has no idea where it's been, yet is just able to take a "snapshot" of the world in it's current state, for each state that the agent is in.
