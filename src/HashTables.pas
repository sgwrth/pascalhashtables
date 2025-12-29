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
  AppendNode(Table, 'pas', 123);
  AppendNode(Table, 'c', 234);
  AppendNode(Table, 'sh', 345);
  AppendNode(Table, 'py', 456);
  AppendNode(Table, 'sql', 567);
  AppendNode(Table, 'js', 678);
  AppendNode(Table, 'php', 7);
  DeleteNode(Table, 'foo');
  AppendNode(Table, 'bat', 8);
  AppendNode(Table, 'go', 9);
  AppendNode(Table, 'cpp', 0);
  DeleteNode(Table, 'bar');
  DisposeTable(Table);
end.
