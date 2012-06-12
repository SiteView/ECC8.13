package de.ajaxgui;

import de.ajaxgui.ext.JsGenerator;

public class ComboBoxItem extends Control {
	private Object notice = null;

	private String text = "";

	public ComboBoxItem(String text) {
		this.text = text;
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxListItem(\"" + text + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}

	public Object getNotice() {
		return notice;
	}

	public String getText() {
		return text;
	}

	public void setNotice(Object notice) {
		this.notice = notice;
	}

	public void setText(String text) {
		this.text = text;
		JsGenerator.get()
				.addLine(getVarName() + ".setLabel(\"" + text + "\");");
	}
}
