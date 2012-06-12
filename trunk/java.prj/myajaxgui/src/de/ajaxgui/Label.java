package de.ajaxgui;

import de.ajaxgui.ext.JsGenerator;

public class Label extends Control {
	private String text = "";

	public Label(String text) {
		this.text = text;
		JsGenerator.get().addLine(
				getVarName() + " = new QxLabel(\"" + text + "\");");
		JsGenerator.get().addLine(getVarName() + ".id = " + getId() + ";");
	}

	public void setText(String text) {
		this.text = text;
		JsGenerator.get().addLine(getVarName() + ".setHtml(\"" + text + "\");");
	}

}
