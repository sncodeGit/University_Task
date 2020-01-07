<allrustext>
{
  for $i in doc("bookstore.xml")/bookstore//*
  where $i[@lang = "rus"]
  for $j in $i | $i//*
  return
    (
    if ($j/text() != '')
      then <text>{$j/text()}</text>
      else $j/text()
    )
}
</allrustext
