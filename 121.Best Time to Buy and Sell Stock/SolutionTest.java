import static org.junit.Assert.*;
import org.junit.*;
 
public class SolutionTest {
 
    private Solution s;
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
    public void test_1() {
        int[] nums = {7,1,5,3,6,4};
        assertEquals(5, s.maxProfit(nums));
    }
    
    @Test
    public void test_2() {
        int[] nums = {7,6,4,3,1};
        assertEquals(0, s.maxProfit(nums));
    }
}
