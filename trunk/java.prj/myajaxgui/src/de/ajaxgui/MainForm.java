package de.ajaxgui;

import de.ajaxgui.ext.ComponentManager;
import de.ajaxgui.ext.EventManager;
import de.ajaxgui.ext.JsGenerator;

public class MainForm {

	public void add(Control control) {
		ComponentManager.get().addComponent(control);
		JsGenerator.get().addLine("doc.add(" + control.getVarName() + ");");
	}

	public void show() {
		while (EventManager.get().processEvents()) {
		}
	}
}
