for $x in doc("bookstore.xml")/bookstore/*
where $x/price>29
return $x/name/text() | $x/title/text()
