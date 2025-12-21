{ Forward declarations. }
procedure InitTable(var Table: HashTable); forward;
procedure InitBucket(var Bucket: NodePtr); forward;
function NewNode(Key: Key; Value: integer) : NodePtr; forward;
procedure InitNode(var Node: NodePtr; Key: Key; Value: integer); forward;

procedure InitTable(var Table: HashTable);
var
  i: integer;
  Buckets: HashTableBuckets;
begin
  for i := 1 to BucketInitialCapacity do
    InitBucket(Buckets[i]);
  Table.Buckets := Buckets;
  Table.Length := 0;
  Table.Capacity := BucketInitialCapacity;
end;

procedure InitBucket(var Bucket: NodePtr);
begin
  Bucket := nil;
end;

function NewNode(Key: Key; Value: integer) : NodePtr;
var
  Node: NodePtr;
begin
  new(Node);
  InitNode(Node, Key, Value);
  NewNode := Node;
end;

procedure InitNode(var Node: NodePtr; Key: Key; Value: integer);
begin
  Node^.NextNode := nil;
  Node^.Key := Key;
  Node^.HashedKey := 0;
  Node^.Value := Value;
end;

