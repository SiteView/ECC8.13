package de.ajaxgui;

import java.text.SimpleDateFormat;
import java.util.Date;

import de.ajaxgui.ext.JsGenerator;

public class DatePicker extends Image {
	private TextField tf = null;

	public String date = "";

	public DatePicker(TextField tf) {
		this(tf, new Date());
	}

	public DatePicker(TextField tf, Date d) {
		super("calendar/scw.gif");
		this.tf = tf;

		date = new SimpleDateFormat("dd.MM.yyyy").format(d);
		tf.setText(date);

		JsGenerator jg = JsGenerator.get();
		jg.addLine(getVarName() + ".setHtmlProperty(\"id\", \"" + getId()
				+ "\");");
		jg.addLine(getVarName() + ".setHtmlProperty(\"value\", \"" + date
				+ "\");");
		// jg
		// .addLine(getVarName()
		// + ".setHtmlProperty(\"onclick\", \"alert('juhu');scwShow(this,
		// this);\");");
		jg
				.addLine(getVarName()
						+ ".addEventListener(QxConst.EVENT_TYPE_CLICK, function() {scwNextAction=dateChangedEvent.runsAfterSCW(this, this);scwShow(document.getElementById(this.id), this);});");
	}

	public void doDateChanged() {
		tf.setText(date);
	}

	public void setDate(Date d) {
		date = new SimpleDateFormat("dd.MM.yyyy").format(d);
		tf.setText(date);
		JsGenerator.get()
				.addLine(
						getVarName() + ".setHtmlProperty(\"value\", \"" + date
								+ "\");");
	}
}
