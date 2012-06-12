package de.ajaxgui.test;

import java.util.ArrayList;

import de.ajaxgui.Button;
import de.ajaxgui.Label;
import de.ajaxgui.ListView;
import de.ajaxgui.ListViewHeader;
import de.ajaxgui.ListViewItem;
import de.ajaxgui.MainForm;

public class ListViewMainForm extends MainForm {

	private ListView lv = null;

	private Label label = null;

	public ListViewMainForm() {
		ListViewHeader lvh = new ListViewHeader();
		lvh.addColumn("Vorname", 100, ListViewHeader.ColumnTypeText);
		lvh.addColumn("Nachname", 150, ListViewHeader.ColumnTypeText);

		lv = new ListView(lvh);
		lv.setLocation(60, 60);
		lv.setDimension(320, 240);
		lv.addSelectionChanged(this, "lvSelectionChanged");
		this.add(lv);

		addData();

		label = new Label("No news");
		label.setLocation(120, 320);
		this.add(label);

		Button b = new Button("Refresh ListView");
		b.setLocation(120, 350);
		b.addClick(this, "refresh");
		this.add(b);
	}

	private void addData() {
		ListViewItem lvi1 = new ListViewItem();
		lvi1.addText("Steve");
		lvi1.addText("Schneider");
		lv.add(lvi1);

		ArrayList<ListViewItem> lvis = new ArrayList<ListViewItem>();
		ListViewItem lvi2 = new ListViewItem();
		lvi2.addText("Anna");
		lvi2.addText("Eichorst");
		lvis.add(lvi2);
		ListViewItem lvi3 = new ListViewItem();
		lvi3.addText("Christian");
		lvi3.addText("Brandt");
		lvis.add(lvi3);
		lv.add(lvis);

		ListViewItem lvi4 = new ListViewItem();
		lvi4.addText("Markus");
		lvi4.addText("Spiekermann");
		lv.add(lvi4);
	}

	public void lvSelectionChanged() {
		ListViewItem selected = lv.getSelected();
		label.setText("Selected: " + selected.getText(0) + " "
				+ selected.getText(1));
	}

	public void refresh() {
		lv.clear();
		label.setText("No News");
		this.addData();
	}
}
