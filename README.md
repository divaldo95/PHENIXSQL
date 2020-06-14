# Data reader from database for PHENIX experiment
It is only a proof of concept yet.
## Prerequisities
* System which runs CERN Root (Tested on Ubuntu 18.04) (you may need to change #include "mysql.h" to #include "mysql/mysql.h)"
* CERN Root (Tested on 6.20/04)
* CMake

## Build
Before compilation set the username, password and database name in [CommonData.hpp](include/CommonData.hpp).
- `git clone https://github.com/divaldo95/PHENIXSQL.git`
- `cd PHENIXSQL && mkdir build && cd build`
- `cmake ../`
- `make -jN` Where N is the number of jobs to run simultaneously

## Run
You need to create a database from [root2SQL](https://github.com/divaldo95/root2SQL) exported SQL scripts. (Use -n filename).
- `./PHENIXSQL`

# Changelog
## 2020-06-14
* Initial version