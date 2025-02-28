# Simulators for Assembly Lines
 Completed during the third semester of a collegiate program, this project number 4. 
 
 a C++ program using workstations processing consumer orders to replicate an industrial assembly line.

 # Project Summary

 This concept uses an assembly line simulation whereby consumer orders pass across a set of workstations.  As customer orders go through the line, each workstation manages inventories and fills particular assembly tasks.

 ## traits

- Several workstations have special powers
- System for customer orders tracking
- inventory control
- production line optimization
- automatic order routing

 ## Technical Applicability

 C++ object-oriented programming ideas are used in construction of the simulator with:

- Custom data structures
- modular class architecture
- Memory management
- File-based configuration

 # Classes

- **Station**: Manages individual workstation inventory and capabilities;
- **CustomerOrder**: tracks customer orders as they pass through the system
- **LineManager**: controls the flow of orders through the assembly line
- **Utilities**: offers helper functions for data management and parsing
- **Workstation**: processes orders and manages transitions between stations.

 ## How It Gets Started

 1. Configuring files specify stations and their capabilities.
 2. Load customer orders from order files.
 3. The line manager sets stations in ideal order.
 4. Orders pass via the assembly line.
 5. Tracking completed and unfinished orders separately

 ## Necessities

 Versions above C++17 & Standard Template Library (STL)
