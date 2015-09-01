# Vispy OSMesa docker container

This is a Dockerfile that builds a container with OSMesa to test vispy
offscreen rendering.

Quick usage :

1. Checkout the *osmesa* vispy branch (in the same directory as the run.sh script)
    ```
    git clone -b osmesa git@github.com:julienr/vispy.git
    ```

2. Start a bash shell in the container with `./run.sh`
3. Run the simple_osmesa.py example 
    ```
    VISPY_GL_LIB=/opt/osmesa_llvmpipe/lib/libGLESv2.so \
    LD_LIBRARY_PATH=/opt/osmesa_llvmpipe/lib/ \
    OSMESA_LIBRARY=/opt/osmesa_llvmpipe/lib/libOSMesa.so \
    PYTHONPATH=/root/vispy \
    python examples/offscreen/simple_osmesa.py
    ```

4. On your host machine, you should have a *vispy/osmesa.png* file that was
   created by the simple_osmesa.py script.
   
   It should look like this :
   
   ![expected osmesa.png image](doc/osmesa.png)

