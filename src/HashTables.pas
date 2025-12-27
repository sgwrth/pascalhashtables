program HashTables;

(*$I include/constants.inc*)

(*$I include/types.inc*)

var
  Table: HashTablePtr;

(*$I include/proceduresandfunctions.inc*)

begin
  new(Table);
  InitTable(Table);
  AppendNode(Table, 'foo', 42);
  AppendNode(Table, 'foo', 42);
end.
