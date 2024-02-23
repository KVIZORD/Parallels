#include <gauss/controller/controller.h>
#include <gauss/view/view.h>

int main() {
  s21::Controller controller;
  s21::View view(controller);

  view.Exec();
  return 0;
}