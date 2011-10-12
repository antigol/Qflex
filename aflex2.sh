#! /bin/bash

# fichier bash

wget "http://cmspc46.epfl.ch/20112012Data/Exercices/20112012semesters.xml"


progenc "20112012semesters.xml" > sortie.bash

bash sortie.bash

