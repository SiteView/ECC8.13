package de.ajaxgui;

import java.util.ArrayList;

import de.ajaxgui.ext.Component;
import de.ajaxgui.ext.JsGenerator;

public class RadioGroup extends Component {

	private ArrayList<RadioButton> radioButtons = new ArrayList<RadioButton>();

	public RadioGroup() {
		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + " = new QxRadioManager();");
		jg.addLine(getVarName() + ".id = " + getId() + ";");
	}

	public void add(RadioButton rb) {
		radioButtons.add(rb);
		JsGenerator.get().addLine(
				getVarName() + ".add(" + rb.getVarName() + ");");
	}
}
