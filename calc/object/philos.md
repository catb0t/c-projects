### const correctness

* all functions are to have parameters they do not mutate and return to their caller marked const
* pointer types shall be const qualified at each level of indirection, eg `const int* const * const * const`, unless it is eg a destructor, which may omit only the first "const", because the data to which the pointers point may change but the pointers themselves will not

* as a result, parameters passed to functions, including heap memory allocated by the caller, are the responsibility of the caller to free after use.
concat_lines is a notable exception but it is implemented that way for brevity.

* all object functions should return copies of data, rather than references to the data, except where explicitly desired, as with eg array_get_ref, which returns a reference to the nth element of an array, useful for when the original object is going to modified, destructed, etc.

as a result, all object types should define at a minimum a _new, _copy and _destruct function, almost analogous to C++'s constructors, copy constructors and destructors.

the NULL pointer is a valid value to indicate an empty array of primitives or in almost all constructors where a pointer is required.

nothing_new(), or the F_t object returned by object_new(t_F, ...) || object_new(..., NULL) should be used to indicate false or an empty collection.

### collections protocol

collection types define at minimum:

```
type_append
type_concat
type_clear
type_delete
type_find
type_get_copy
type_get_ref
type_isempty
type_insert
type_inspect
type_join
type_length
type_resize
```

* For ordered sequences, the `signed size_t idx` member should refer to the highest accessible index at a given time.

* A value of -1 for `idx` denotes an empty collection (`data` may be null) but retrival of negative indicies should refer to the end of the list. (WIP)


each object type should define:
```
type_copy
type_destruct
type_equals
type_new
type_see
```
on scalars:
```
type_eq
type_gt
type_lt
```

```
ignore me

static const char OBJTYPE_CHARS[] = {
  [t_F]        = 'f',
  [t_T]        = 't',
  [t_number]   = 'n',
  [t_fixwid]   = 'z',
  [t_string]   = 's',
  [t_func]     = 'q',
  [t_array]    = 'a',
  [t_assoc]    = 'o',
  [t_hash]     = 'h',
  [t_pair]     = 'p',
  [t_realint]  = 'i',
  [t_realuint] = 'u',
  [t_realchar] = 'c',
};

_Static_assert(
  ( (sizeof OBJTYPE_CHARS) / (sizeof (char)) == NUM_OBJTYPES),
  "CHAR_2OBJTYPE has too few or too many values"
);

static const objtype_t CHAR_2OBJTYPE[] = {
  ['f'] = t_F,
  ['t'] = t_T,
  ['n'] = t_number,
  ['z'] = t_fixwid,
  ['s'] = t_string,
  ['q'] = t_func,
  ['a'] = t_array,
  ['h'] = t_hash,
  ['p'] = t_pair,
  ['i'] = t_realint,
  ['c'] = t_realchar
};

_Static_assert(
  ( (sizeof CHAR_2OBJTYPE) / (sizeof (objtype_t)) == ('z' + 1)),
  "CHAR_2OBJTYPE has too few or too many values"
);
```