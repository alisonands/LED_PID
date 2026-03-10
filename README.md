# 2dof LED position control with photoresistors
- This project aims to control the position of LEDs based on feedback from photoresistors. 

## Setup
- Triangular setup of photoresistors(PR)
- Error in x direction: PR3 - PR2
- Error in y direction: ((PR3 + PR2)/2) - PR1


<img src="images/setup.gif" alt="setup" width="50%" />
<img src="images/PID_control.gif" alt="setup" width="50%" />


## Caveats
- Unstable when led is outside of triangular perimeter.