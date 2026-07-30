cmd_/home/javohir/hw3/4/Module.symvers := sed 's/\.ko$$/\.o/' /home/javohir/hw3/4/modules.order | scripts/mod/modpost -m -a  -o /home/javohir/hw3/4/Module.symvers -e -i Module.symvers   -T -
