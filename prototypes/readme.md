# notebooks
This document contains information on setting up a python virtual environment with `Jupyter` support.

## Prototype Virtual Environment (Local)

Below are setup instructions for execution of the notebook locally in a virtual environment. 

It will be assumed that the local directory of the project is `./prototypes`. 
Please adjust as necessary for environment specific deployments. 

See [venv documentation](https://docs.python.org/3/library/venv.html) for more details.

```bash
python3 --version
pip3 --version
cd <this-dir>
python3 -m venv ./venv
source ./venv/bin/activate
pip3 install -r requirements.txt
python3 -m ipykernel install --user --name=venv --display-name "Elevator Prototypes"
jupyter notebook
```

Select the Kernel in Jupyter. When creating a new notebook or opening an existing one, navigate to the "Kernel" menu, then "Change kernel" and select "Elevator Prototypes". This ensures your notebook runs within the isolated virtual environment.

When completed close the notebook environment with `CRTL+C` and respond to the dialog option with `y`. Finally, deactivate the virtual environment.

```bash
deactivate
```
