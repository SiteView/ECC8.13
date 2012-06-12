package de.ajaxgui;

import de.ajaxgui.ext.JsGenerator;

public class UserControl extends ControlContainer {

	public UserControl() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxCanvasLayout();");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}

	public void addMainForm(Control control) {
		super.addMainForm(control);
	}
}
