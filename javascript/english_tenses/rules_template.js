console.log('tenses = {');
for(let x1 of [ 'positive', 'negative' ]) {
  for(let x2 of [ 'statement', 'question' ]) {
    for(let x3 of [ 'past', 'present', 'future' ]) {
      for(let x4 of [ 'nonPerfect', 'perfect' ]) {
        for(let x5 of [ 'simple', 'continuous' ]) {
          for(let x6 of [ 'I', 'he she it', 'we you they' ]) {
            console.log(`  '${ x1 } ${ x2 } ${ x3 } ${ x4 } ${ x5 } ${ x6 }': '???',`);
          }
        }
      }
    }
  }
}
console.log('};');
