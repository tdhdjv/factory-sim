#pragma once
#include "ui_view.h"
#include "backend/machine_base.h"

namespace LongDay {
	class Inspector: public UIView{
	private:
		MachineBase* selectedMachine;
	public:
		Inspector();
		void draw() override;
		void select_machine(MachineBase* machine);
	};
}
