clang-format -i include/ModbusAsync.h
clang-format -i src/ModbusAsync.c
clang-format -i tests/console/main.c
clang-format -i tests/gtk/gtk_app.c

python ~/x/line.py include/ModbusAsync.h
python ~/x/line.py src/ModbusAsync.c
python ~/x/line.py tests/console/main.c
python ~/x/line.py tests/gtk/gtk_app.c
