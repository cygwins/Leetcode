import static org.junit.Assert.*;
import org.junit.*;
 
public class SolutionTest {
 
    private Solution s;
    private java.util.List nums;
    private int k;
 
    /**
     * Sets up the test fixture. 
     * (Called before every test case method.)
     */
    @Before
    public void setUp() {
        s = new Solution();
    }
 
    /**
     * Tears down the test fixture. 
     * (Called after every test case method.)
     */
    @After
    public void tearDown() {
        s = null;
    }
    
    @Test
    public void testStandard() {
        int[] nums = {1,2,3,4,5};
        k = 1;
        assertEquals("Standard case", 4, s.findPairs(nums, k));
    }
    
    @Test
    public void testUnique() {
        int[] nums = {3,1,4,1,5};
        k = 2;
        assertEquals("Duplicates case", 2, s.findPairs(nums, k));
    }
    
    @Test
    public void testZeroK() {
        int[] nums = {1,3,1,5,4};
        k = 0;
        assertEquals("k=0 case", 1, s.findPairs(nums, k));
    }
}
