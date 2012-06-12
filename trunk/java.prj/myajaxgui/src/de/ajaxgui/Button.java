package de.ajaxgui;

import de.ajaxgui.ext.JsGenerator;

public class Button extends AbstractButton {
	public Button(String text) {
		super(text);
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxButton(\"" + text + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}

	public Button(String text, String icon) {
		this(text);
		JsGenerator.get().addLine(getVarName() + ".setIcon(\"" + icon + "\");");
	}

	public void addClick(Object o, String func) {
		super.addClick(o, func);
	}
}
