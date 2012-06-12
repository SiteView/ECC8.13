package de.ajaxgui;

import de.ajaxgui.ext.ComponentManager;
import de.ajaxgui.ext.JsGenerator;

public abstract class ControlContainer extends Control {

	public void add(Control control) {
		ComponentManager.get().addComponent(control);
		JsGenerator.get().addLine(
				this.getVarName() + ".add(" + control.getVarName() + ");");
	}

	protected void addMainForm(Control control) {
		ComponentManager.get().addComponent(control);
		JsGenerator.get().addLine("doc.add(" + control.getVarName() + ");");
	}
}
