#pragma once
#include "service.h"
#include "validare.h"

typedef struct {
	ServiceProdus* serviceProdus;
}UI;

UI creeazaUI(ServiceProdus* serviceProdus);

void run(UI* ui);

void addUiProdus(UI* ui);

void updateUiProdus(UI* ui);

void removeUiProdus(UI* ui);

void viewSortedUiProdus(UI* ui);