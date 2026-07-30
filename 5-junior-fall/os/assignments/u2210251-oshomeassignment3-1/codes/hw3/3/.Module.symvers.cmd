cmd_/home/javohir/hw3/3/Module.symvers := sed 's/\.ko$$/\.o/' /home/javohir/hw3/3/modules.order | scripts/mod/modpost -m -a  -o /home/javohir/hw3/3/Module.symvers -e -i Module.symvers   -T -
