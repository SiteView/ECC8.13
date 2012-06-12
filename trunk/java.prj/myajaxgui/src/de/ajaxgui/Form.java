package de.ajaxgui;

import de.ajaxgui.ext.Event;
import de.ajaxgui.ext.EventManager;
import de.ajaxgui.ext.JsGenerator;

public class Form extends ControlContainer {

	private String title = "";

	public Form() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxWindow();");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}

	public void addMainForm(Control control) {
		super.addMainForm(control);
	}

	public void close() {
		JsGenerator.get().addLine(getVarName() + ".close();");
		Event e = new Event(Event.Type.CLOSE);
		e.setComponentId(this.getId());
		EventManager.get().addEvent(e);
	}

	public void showDialog() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + ".setModal(true);");
		jg.addLine(getVarName() + ".setShowClose(false);");
		jg.addLine(getVarName() + ".setShowMaximize(false);");
		jg.addLine(getVarName() + ".setShowMinimize(false);");
		// jg(getVarName() + ".setMoveable(false);");
		jg.addLine(getVarName() + ".setResizeable(false);");
		// jg(getVarName() + ".setShowIcon(false);");
		jg.addLine(getVarName() + ".setCaption(\"" + title + "\");");
		jg.addLine(getVarName() + ".open();");
		while (EventManager.get().processEvents()) {
		}
	}

	public void setTitle(String title) {
		this.title = title;
	}
}
