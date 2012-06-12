package de.ajaxgui.test;

import de.ajaxgui.ComboBox;
import de.ajaxgui.ComboBoxItem;
import de.ajaxgui.Label;
import de.ajaxgui.MainForm;

public class ComboBoxMainForm extends MainForm {

	private ComboBox cb = null;

	private Label label = null;

	public ComboBoxMainForm() {
		cb = new ComboBox();
		cb.setTop(20);
		cb.setLeft(20);
		cb.addSelectionChanged(this, "cb1SelectionChanged");
		this.add(cb);

		ComboBoxItem cbi1 = new ComboBoxItem("Item 1");
		cb.add(cbi1);
		ComboBoxItem cbi2 = new ComboBoxItem("Item 2");
		cb.add(cbi2);
		ComboBoxItem cbi3 = new ComboBoxItem("Item 3");
		cb.add(cbi3);
		cb.setSelected(cbi3);
		ComboBoxItem cbi4 = new ComboBoxItem("Item 4");
		cb.add(cbi4);

		label = new Label("Item 3");
		label.setTop(60);
		label.setLeft(40);
		this.add(label);
	}

	public void cb1SelectionChanged() {
		label.setText("Selected: " + cb.getSelected().getText());
	}
}
