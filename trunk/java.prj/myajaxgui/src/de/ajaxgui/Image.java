package de.ajaxgui;

import de.ajaxgui.ext.JsGenerator;

public class Image extends Control {

	private String uri = "";

	public Image(String uri) {
		this.uri = uri;
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxImage(\"" + uri + "\");");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}

	public void setUri(String uri) {
		this.uri = uri;
		JsGenerator.get()
				.addLine(getVarName() + ".setSource(\"" + uri + "\");");
	}
}
