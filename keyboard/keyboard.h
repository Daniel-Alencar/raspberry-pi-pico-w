#include <pico/stdlib.h>

void setup_keyboard(uint columns[], uint rows[]) {

  // Calcular a quantidade de elementos
  // int columns_length = sizeof(columns) / sizeof(columns[0]);
  // int rows_length = sizeof(rows) / sizeof(rows[0]);

  int i;
  for(i = 0; i < 4; i++) {
    gpio_init(rows[i]);
    gpio_set_dir(rows[i], GPIO_OUT);
    gpio_put(rows[i], true);
  }

  for(i = 0; i < 4; i++) {
    gpio_init(columns[i]);
    gpio_set_dir(columns[i], GPIO_IN);
  }
}

uint pressioned_column(uint columns[]) {

  // Calcular a quantidade de elementos
  // int columns_length = sizeof(columns) / sizeof(columns[0]);

  bool value = false;
  for(int i = 0; i < 4; i++) {
    value = gpio_get(columns[i]);
    if(value) {
      return i;
    }
  }
  return -1;
}

uint pressioned_row(uint rows[], uint columns[], uint pressioned_column) {

  // Calcular a quantidade de elementos
  // int rows_length = sizeof(rows) / sizeof(rows[0]);

  bool value = true;
  for(int i = 0; i < 4; i++) {
    gpio_put(rows[i], false);
    value = gpio_get(columns[pressioned_column]);
    gpio_put(rows[i], true);
    if(!value) {
      return i;
    }
  }
  return -1;
}

char get_pressioned_key(
  char KEY_MAP[4][4], uint rows[], uint columns[]
) {
  uint row;
  uint column = pressioned_column(columns);
  if(column >= 0) {
    row = pressioned_row(rows, columns, column);
    if(row >= 0) {
      return KEY_MAP[row][column];
    }
  }
  return '\0';
}