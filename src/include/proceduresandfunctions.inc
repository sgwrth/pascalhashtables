(* Forward declarations. *)
procedure InitTable(Table: HashTablePtr); forward;
procedure InitBucket(var Bucket: NodePtr); forward;
function NewNode(Key: Key; Value: integer) : NodePtr; forward;
procedure InitNode(var Node: NodePtr; Key: Key; Value: integer); forward;
function GetHashedKey(Key: Key) : integer; forward;
function GetTargetBucket(Table: HashTablePtr; HashedKey: integer) : integer; forward;
function IsFinalNode(Node: NodePtr) : boolean; forward;
function AreKeysEqual(Key1, Key2: Key): boolean; forward;
function KeyExists(Table: HashTablePtr; Bucket: integer; Key: Key) : boolean; forward;
procedure IncrementNodeCounter(Table: HashTablePtr); forward;
procedure EchoNumberOfNodes(Table: HashTablePtr); forward;
function NeedsResizing(Table: HashTablePtr): boolean; forward;
procedure AppendNode(Table: HashTablePtr; Key: Key; Value: integer); forward;
procedure UnlinkNodeForDelete(Table: HashTablePtr; TargetBucket: integer; Node: NodePtr); forward;
procedure PrintDeletedKeyInfo(Key: Key); forward;
procedure DeleteNode(Table: HashTablePtr; Key: Key); forward;

procedure InitTable(Table: HashTablePtr);
var
  I: integer;
  Buckets: HashTableBuckets;
begin
  for I := 1 to BucketInitialCapacity do
    InitBucket(Buckets[I]);
  Table^.Buckets := Buckets;
  Table^.Length := 0;
  Table^.Capacity := BucketInitialCapacity;
end;

procedure DisposeTable(Table: HashTablePtr);
begin
  dispose(Table);
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
  Node^.PrevNode := nil;
  Node^.NextNode := nil;
  Node^.Key := Key;
  Node^.HashedKey := GetHashedKey(Key);
  Node^.Value := Value;
end;

function GetHashedKey(Key: Key) : integer;
var
  HashedKey: integer;
  OrdinalValue: integer;
  Pos: integer;
begin
  HashedKey := 0;
  Pos := 1;
  while (Pos <= KeyMaxLen) and (ord(Key[Pos]) <> 0) do
  begin
    OrdinalValue := ord(Key[Pos]);
    HashedKey := HashedKey * 31 + OrdinalValue;
    Pos := Pos + 1;
  end;
  GetHashedKey := HashedKey; 
end;

function GetTargetBucket(Table: HashTablePtr; HashedKey: integer) : integer;
begin
  GetTargetBucket := abs(HashedKey) mod Table^.Capacity + 1;
end;

function IsFinalNode(Node: NodePtr) : boolean;
begin
  IsFinalNode := Node^.NextNode = nil;
end;

function AreKeysEqual(Key1, Key2: Key): boolean;
var
  Index: integer;
  KeysMatching: boolean;
begin
  KeysMatching := true;
  Index := 1;
  while (Index <= KeyMaxLen) and (KeysMatching) do
  begin
    if Key1[Index] <> Key2[Index] then
      KeysMatching := false
    else
      Index := Index + 1;
  end;
  AreKeysEqual := KeysMatching;
end;

function KeyExists(Table: HashTablePtr; Bucket: integer; Key: Key) : boolean;
var
  KeyFound: boolean;
  CurrentNode: NodePtr;
begin
  KeyFound := false;
  CurrentNode := Table^.Buckets[Bucket];
  while CurrentNode <> nil do
  begin
    if AreKeysEqual(CurrentNode^.Key, Key) then
    begin
      KeyFound := true;
      CurrentNode := nil; (* Exit loop. *)
    end
    else
      CurrentNode := CurrentNode^.NextNode;
  end;
  KeyExists := KeyFound;
end;

procedure IncrementNodeCounter(Table: HashTablePtr);
begin
  Table^.AmountOfNodes := Table^.AmountOfNodes + 1;
end;

procedure DecrementNodeCounter(Table: HashTablePtr);
begin
  Table^.AmountOfNodes := Table^.AmountOfNodes - 1;
end;

procedure EchoNumberOfNodes(Table: HashTablePtr);
begin
  write('Node added.  Total nodes: ');
  writeln(Table^.AmountOfNodes:0);
end;

procedure AppendNode(Table: HashTablePtr; Key: Key; Value: integer);
var
  BucketNumber: integer;
  CurrentNode: NodePtr;
begin
  BucketNumber := GetTargetBucket(Table, GetHashedKey(Key));
  if Table^.Buckets[BucketNumber] = nil then
    begin
      Table^.Buckets[BucketNumber] := NewNode(Key, Value);
      IncrementNodeCounter(Table);
      EchoNumberOfNodes(Table);
    end
  else
  begin
    if not KeyExists(Table, BucketNumber, Key) then
    begin
      CurrentNode := Table^.Buckets[BucketNumber];
      while not IsFinalNode(CurrentNode) do
        CurrentNode := CurrentNode^.NextNode;
      CurrentNode^.NextNode := NewNode(Key, Value);
      CurrentNode^.NextNode^.PrevNode := CurrentNode;
      IncrementNodeCounter(Table);
      EchoNumberOfNodes(Table);
    end
    else
      writeln('Key already exists.');
  end;
end;

procedure UnlinkNodeForDelete(Table: HashTablePtr; TargetBucket: integer; Node: NodePtr);
begin
    if Node^.PrevNode <> nil then
      Node^.PrevNode^.NextNode := Node^.NextNode
    else
      Table^.Buckets[TargetBucket] := Node^.NextNode;
    if Node^.NextNode <> nil then
      Node^.NextNode^.PrevNode := Node^.PrevNode;
end;

procedure PrintDeletedKeyInfo(Key: Key);
begin
    write('Node with key [');
    write(Key);
    writeln('] deleted.');
end;

procedure PrintKeyNotFound();
begin
    writeln('Key not found.')
end;

function NeedsResizing(Table: HashTablePtr): boolean;
var
  ExcedesThreshold: boolean;
begin
  ExcedesThreshold := false;
  NeedsResizing := ExcedesThreshold;
end;

procedure DeleteNode(Table: HashTablePtr; Key: Key);
var
  TargetBucket: integer;
  CurrentNode: NodePtr;
  KeyFound: boolean;
begin
  TargetBucket := GetTargetBucket(Table, GetHashedKey(Key));
  CurrentNode := Table^.Buckets[TargetBucket];
  KeyFound := false;
  if CurrentNode = nil then
    PrintKeyNotFound()
  else
  begin
    while CurrentNode <> nil do
    begin
      if AreKeysEqual(CurrentNode^.Key, Key) then
      begin
        KeyFound := true;
        UnlinkNodeForDelete(Table, TargetBucket, CurrentNode);
        Dispose(CurrentNode);
        DecrementNodeCounter(Table);
        CurrentNode := nil;
        PrintDeletedKeyInfo(Key);
      end
      else
        CurrentNode := CurrentNode^.NextNode;
    end;
  end;
  if not KeyFound then
    PrintKeyNotFound();
end;
