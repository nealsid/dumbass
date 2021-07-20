# dumbass
DumbAss is a prototype language.  One feature I'd like to implement is something called "named exception handling blocks", i.e.

```
func foo(...) {

   statement that throws on-exception handleexception
   statement that throws on-exception handleanotherexception
   .
   .
   .
   return 5;
   
   handleexception {
   
   
   }
   
   handleanotherexception {
   
   
   }
}
```

In order to separate the frequent code paths from the infrequent ones. 
