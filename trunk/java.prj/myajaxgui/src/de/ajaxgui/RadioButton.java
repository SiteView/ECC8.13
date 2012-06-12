package de.ajaxgui;

import de.ajaxgui.ext.JsGenerator;

public class RadioButton extends AbstractButton {
	public RadioButton(String text) {
		super(text);
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxRadioButton(\"" + text + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}

	public void addClick(Object o, String func) {
		super.addClick(o, func);
	}
}
