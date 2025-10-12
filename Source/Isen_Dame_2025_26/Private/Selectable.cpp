// Fill out your copyright notice in the Description page of Project Settings.


#include "Selectable.h"

// Add default functionality here for any ISelectable functions that are not pure virtual.
void ISelectable::Select()
{
}

void ISelectable::Unselect()
{
}

bool ISelectable::IsAPawn()
{
	return false;
}
