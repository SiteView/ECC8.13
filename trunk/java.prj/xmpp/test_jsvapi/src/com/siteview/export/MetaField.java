package com.siteview.export;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.jdom.input.SAXBuilder;

import com.focus.db.DBCon;
import com.focus.db.QueryResult;
import com.focus.util.Util;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.Text;

public class MetaField {
	public static String writeMeta(DBCon con, String SV_TYPE,
			HashMap<String, String> metaMap) throws Exception {

		if(SV_TYPE.equals("password")&&metaMap.get("sv_itemvalue1")!=null)
			System.out.println("find");
		
		String fieldId = Util.createId();

		con
				.setSQL("insert into sv_field_type(FIELD_TYPE,HAS_TABLE)values(:FIELD_TYPE,'F')");
		con.setParameter("FIELD_TYPE", SV_TYPE);
		con.excuteNoWarningPk();

		Iterator iterator = metaMap.keySet().iterator();

		while (iterator.hasNext()) {
			String key = iterator.next().toString();
			con
					.setSQL("insert into sv_field_type_attr(FIELD_TYPE,ATTR_NAME)values(:FIELD_TYPE,:ATTR_NAME)");
			con.setParameter("FIELD_TYPE", SV_TYPE);
			con.setParameter("ATTR_NAME", key);
			con.excuteNoWarningPk();
		}

		con
				.setSQL("insert into sv_field(FIELDID,FIELD_TYPE)values(:FIELDID,:FIELD_TYPE)");
		con.setParameter("FIELDID", fieldId);
		con.setParameter("FIELD_TYPE", SV_TYPE);
		con.execute();

		iterator = metaMap.keySet().iterator();
		while (iterator.hasNext()) {
			String key = iterator.next().toString();

			con
					.setSQL("insert into sv_field_attr(FIELDID,ATTR_NAME,ATTR_VALUE)values(:FIELDID,:ATTR_NAME,:ATTR_VALUE)");
			con.setParameter("FIELDID", fieldId);
			con.setParameter("ATTR_NAME", key);
			con.setParameter("ATTR_VALUE", metaMap.get(key).toString());
			con.execute();
		}

		return fieldId;

	}
}
