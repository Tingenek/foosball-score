xquery version "1.0";
declare function local:add-ns-node(
    $elem as document-node(),
    $prefix as xs:string,
    $ns-uri as xs:string
  ) as element()
{
  element { QName($ns-uri, concat($prefix, ":x")) }{ $elem }/*
};

local:add-ns-node(., "p1", "uri2")