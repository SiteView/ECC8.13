package de.ajaxgui.ext;

import de.ajaxgui.Label;

public class Loading extends Label {

	public Loading(String text) {
		super(text);
		this.setVisibility(false);
		JsGenerator.get().addLine(
				getVarName() + ".setBackgroundColor(\"red\");");
	}
}
